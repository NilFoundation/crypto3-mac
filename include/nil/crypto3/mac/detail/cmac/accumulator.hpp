//---------------------------------------------------------------------------//
// Copyright (c) 2018-2019 Nil Foundation AG
// Copyright (c) 2018-2019 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_ACCUMULATORS_BLOCK_HPP
#define CRYPTO3_ACCUMULATORS_BLOCK_HPP

#include <boost/container/static_vector.hpp>

#include <boost/parameter/value_type.hpp>

#include <boost/accumulators/framework/accumulator_base.hpp>
#include <boost/accumulators/framework/extractor.hpp>
#include <boost/accumulators/framework/depends_on.hpp>
#include <boost/accumulators/framework/parameters/sample.hpp>

#include <nil/crypto3/detail/make_array.hpp>
#include <nil/crypto3/detail/static_digest.hpp>

namespace nil {
    namespace crypto3 {
        namespace accumulators {
            namespace impl {
                template<typename Mode>
                struct mac_impl : boost::accumulators::accumulator_base {
                protected:
                    typedef Mode mode_type;
                    typedef typename Mode::cipher_type cipher_type;
                    typedef typename Mode::padding_type padding_type;

                    typedef typename mode_type::finalizer_type finalizer_type;

                    constexpr static const std::size_t word_bits = mode_type::word_bits;
                    typedef typename mode_type::word_type word_type;

                    constexpr static const std::size_t state_bits = mode_type::state_bits;
                    constexpr static const std::size_t state_words = mode_type::state_words;
                    typedef typename mode_type::state_type state_type;

                    constexpr static const std::size_t block_bits = mode_type::block_bits;
                    constexpr static const std::size_t block_words = mode_type::block_words;
                    typedef typename mode_type::block_type block_type;

                    typedef boost::container::static_vector<word_type, block_words> cache_type;

                public:
                    typedef mac::static_digest<block_bits> result_type;

                    template<typename Args>
                    mac_impl(const Args &args) : cipher(args[accumulators::cipher]), seen(0) {
                    }

                    template<typename ArgumentPack>
                    inline void operator()(const ArgumentPack &args) {
                        return process(args[boost::accumulators::sample]);
                    }

                    template<typename ArgumentPack>
                    inline result_type result(const ArgumentPack &args) const {
                        result_type res = digest;

                        if (!cache.empty()) {
                            block_type ib = {0};
                            std::move(cache.begin(), cache.end(), ib.begin());
                            block_type ob = cipher.end_message(ib);
                            std::move(ob.begin(), ob.end(), std::inserter(res, res.end()));
                        }

                        if (seen % block_bits) {
                            finalizer_type(block_bits - seen % block_bits)(res);
                        } else {
                            finalizer_type(0)(res);
                        }

                        return res;
                    }

                protected:
                    inline void process(const block_type &block, std::size_t bits) {
                    }

                    block::cipher<cipher_type, mode_type, padding_type> cipher;

                    std::size_t seen;
                    cache_type cache;
                    result_type digest;
                };
            }    // namespace impl

            namespace tag {
                template<typename MessageAuthenticationCode>
                struct mac : boost::accumulators::depends_on<> {
                    typedef Mode mode_type;

                    /// INTERNAL ONLY
                    ///

                    typedef boost::mpl::always<accumulators::impl::mac_impl<MessageAuthenticationCode>> impl;
                };
            }    // namespace tag

            namespace extract {
                template<typename MessageAuthenticationCode, typename AccumulatorSet>
                typename boost::mpl::apply<AccumulatorSet, tag::mac<MessageAuthenticationCode>>::type::result_type
                    mac(const AccumulatorSet &acc) {
                    return boost::accumulators::extract_result<tag::mac<MessageAuthenticationCode>>(acc);
                }
            }    // namespace extract
        }        // namespace accumulators
    }            // namespace crypto3
}    // namespace nil

#endif    // CRYPTO3_ACCUMULATORS_BLOCK_HPP
