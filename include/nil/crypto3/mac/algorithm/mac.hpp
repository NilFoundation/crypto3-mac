//---------------------------------------------------------------------------//

// Copyright (c) 2019-2020 Mikhail Komarov <nemo@nil.foundation>
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------//

#ifndef CRYPTO3_MAC_ALGORITHM_HPP
#define CRYPTO3_MAC_ALGORITHM_HPP

#include <cstdint>

namespace nil {
    namespace crypto3 {
        namespace mac {
            /*!
             * @brief
             * @tparam Mac
             */
            template<typename Mac>
            struct nop_padding {
                typedef std::size_t size_type;

                typedef Mac mac_type;

                typedef typename mac_type::block_type block_type;
            };
        }    // namespace mac
        /*!
         * @defgroup mac Message Authentication Codes
         *
         * @brief A message authentication code (MAC) can be used to verify the
         * integrity of data and the authenticity of a message.
         *
         * @defgroup mac_algorithms Algorithms
         * @ingroup mac
         * @brief Algorithms are meant to provide message authentication codes computation
         * interface similar to STL algorithms' one.
         */
    }    // namespace crypto3
}    // namespace nil

#endif    // CRYPTO3_MAC_HPP
