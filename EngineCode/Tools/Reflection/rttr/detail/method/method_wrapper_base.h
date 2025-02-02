/************************************************************************************
*                                                                                   *
*   Copyright (c) 2014, 2015 - 2016 Axel Menzel <info@rttr.org>                     *
*                                                                                   *
*   This file is part of RTTR (Run Time Type Reflection)                            *
*   License: MIT License                                                            *
*                                                                                   *
*   Permission is hereby granted, free of charge, to any person obtaining           *
*   a copy of this software and associated documentation files (the "Software"),    *
*   to deal in the Software without restriction, including without limitation       *
*   the rights to use, copy, modify, merge, publish, distribute, sublicense,        *
*   and/or sell copies of the Software, and to permit persons to whom the           *
*   Software is furnished to do so, subject to the following conditions:            *
*                                                                                   *
*   The above copyright notice and this permission notice shall be included in      *
*   all copies or substantial portions of the Software.                             *
*                                                                                   *
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
*   SOFTWARE.                                                                       *
*                                                                                   *
*************************************************************************************/

#ifndef RTTR_METHOD_WRAPPER_BASE_H_
#define RTTR_METHOD_WRAPPER_BASE_H_

#include "rttr/detail/base/core_prerequisites.h"
#include "rttr/detail/metadata/metadata_handler.h"
#include "rttr/type.h"
#include "rttr/variant.h"
#include "rttr/parameter_info.h"
#include "rttr/access_levels.h"


#include <string>
#include <vector>

namespace rttr
{
class type;
class argument;
class instance;

namespace detail
{

/*!
 * Abstract class for a method.
 * 
 * This is the base class for all methods.
 * You can invoke the method via method_wrapper_base::invoke.
 */
class RTTR_API method_wrapper_base
{
    public:
        method_wrapper_base();
        virtual ~method_wrapper_base();

        void set_name(const char* name);
        const char* get_name() const;
        void set_declaring_type(type declaring_type);
        type get_declaring_type() const;
		type get_declaring_type_ptr() const;
        std::string get_signature() const;

        virtual access_levels get_access_level() const = 0;
        virtual type get_return_type() const = 0;
        virtual bool is_static() const = 0;
        virtual std::vector<bool> get_is_reference() const = 0;
        virtual std::vector<bool> get_is_const() const = 0;
        virtual std::vector<parameter_info> get_parameter_infos() const = 0;
        virtual variant get_metadata(const variant& key) const = 0;

        virtual variant invoke(instance& object) const = 0;
        virtual variant invoke(instance& object, argument& arg1) const = 0;
        virtual variant invoke(instance& object, argument& arg1, argument& arg2) const = 0;
        virtual variant invoke(instance& object, argument& arg1, argument& arg2, argument& arg3) const = 0;
        virtual variant invoke(instance& object, argument& arg1, argument& arg2, argument& arg3,
                               argument& arg4) const = 0;
        virtual variant invoke(instance& object, argument& arg1, argument& arg2, argument& arg3,
                               argument& arg4, argument& arg5) const = 0;
        virtual variant invoke(instance& object, argument& arg1, argument& arg2, argument& arg3,
                               argument& arg4, argument& arg5, argument& arg6) const = 0;

        virtual variant invoke_variadic(const instance& object, std::vector<argument>& args) const = 0;

    private:
        const char* m_name;
        type        m_declaring_type;		///< @attention It's declaring type pointer now. It's easier to retrive original class type from pointer then vice versa.
};

} // end namespace detail
} // end namespace rttr

#endif // RTTR_METHOD_WRAPPER_BASE_H_
