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

#ifndef RTTR_PROPERTY_WRAPPER_MEMBER_OBJECT_H_
#define RTTR_PROPERTY_WRAPPER_MEMBER_OBJECT_H_


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// property_wrapper_member_base - hack for getting member pointer

template< typename C, typename A >
class property_wrapper_member_base : public property_wrapper_base
{
public:
	using accessor = A (C::*);

	property_wrapper_member_base( accessor acc )
		:	m_acc( acc )
	{}

	inline accessor		GetPtr() const	{ return m_acc; }

protected:
    accessor m_acc;
};


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// pointer to member - read write

template<typename C, typename A, access_levels Acc_Level, std::size_t Metadata_Count>
class property_wrapper<member_object_ptr, A(C::*), void, Acc_Level, return_as_copy, set_value, Metadata_Count> : public property_wrapper_member_base< C, A >, public metadata_handler<Metadata_Count>
{
    using accessor = A (C::*);
    public:
        property_wrapper(accessor acc, std::array<metadata, Metadata_Count> metadata_list)
        :   metadata_handler<Metadata_Count>(std::move(metadata_list)),
            property_wrapper_member_base< C, A >(acc)
        { 
        }

        access_levels get_access_level() const { return Acc_Level; }
        bool is_readonly()  const   { return false; }
        bool is_static()    const   { return false; }
        type get_type()     const   { return type::get<A>(); }
        bool is_array()     const   { return detail::is_array<A>::value; }

        variant get_metadata(const variant& key) const { return metadata_handler<Metadata_Count>::get_metadata(key); }

        bool set_value(instance& object, argument& arg) const
        {
            C* ptr = object.try_convert<C>();
            if (ptr && arg.is_type<A>())
                return property_accessor<A>::set_value((ptr->*m_acc), arg);
            else
                return false;
        }

        variant get_value(instance& object) const
        {
            if (C* ptr = object.try_convert<C>())
                return variant((ptr->*m_acc));
            else
                return variant();
        }


};


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// pointer to member - read only (because of std::false_type)

template<typename C, typename A, access_levels Acc_Level, std::size_t Metadata_Count>
class property_wrapper<member_object_ptr, A(C::*), void, Acc_Level, return_as_copy, read_only, Metadata_Count> : public property_wrapper_member_base< C, A >, public metadata_handler<Metadata_Count>
{
    using accessor = A (C::*);
    public:
        property_wrapper(accessor acc, std::array<metadata, Metadata_Count> metadata_list)
        :   metadata_handler<Metadata_Count>(std::move(metadata_list)),
            property_wrapper_member_base< C, A >(acc)
        {
        }

        access_levels get_access_level() const { return Acc_Level; }
        bool is_readonly()  const   { return true; }
        bool is_static()    const   { return false; }
        type get_type()     const   { return type::get<A>(); }
        bool is_array()     const   { return detail::is_array<A>::value; }

        variant get_metadata(const variant& key) const { return metadata_handler<Metadata_Count>::get_metadata(key); }

        bool set_value(instance& object, argument& arg) const
        {
            return false;
        }

        variant get_value(instance& object) const
        {
            if (C* ptr = object.try_convert<C>())
                return variant((ptr->*m_acc));
            else
                return variant();
        }
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// pointer to member - read write

template<typename C, typename A, access_levels Acc_Level, std::size_t Metadata_Count>
class property_wrapper<member_object_ptr, A(C::*), void, Acc_Level, return_as_ptr, set_as_ptr, Metadata_Count> : public property_wrapper_member_base< C, A >, public metadata_handler<Metadata_Count>
{
    using accessor = A (C::*);
    public:
        property_wrapper(accessor acc, std::array<metadata, Metadata_Count> metadata_list)
        :   metadata_handler<Metadata_Count>(std::move(metadata_list)),
            property_wrapper_member_base< C, A >(acc)
        {
            static_assert(!std::is_pointer<A>::value, "The data type of the property is already a pointer type! The given policy cannot be used for this property.");
        }

        access_levels get_access_level() const { return Acc_Level; }
        bool is_readonly()  const   { return false; }
        bool is_static()    const   { return false; }
        type get_type()     const   { return type::get<A*>(); }
        bool is_array()     const   { return detail::is_array<A>::value; }

        variant get_metadata(const variant& key) const { return metadata_handler<Metadata_Count>::get_metadata(key); }

        bool set_value(instance& object, argument& arg) const
        {
            C* ptr = object.try_convert<C>();
            if (ptr && arg.is_type<A*>())
            {
                return property_accessor<A*>::set_value(&(ptr->*m_acc), arg);
            }
            else
            {
                return false;
            }
        }

        variant get_value(instance& object) const
        {
            if (C* ptr = object.try_convert<C>())
                return variant(&(ptr->*m_acc));
            else
                return variant();
        }
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
// pointer to member - read only

template<typename C, typename A, access_levels Acc_Level, std::size_t Metadata_Count>
class property_wrapper<member_object_ptr, A(C::*), void, Acc_Level, return_as_ptr, read_only, Metadata_Count> : public property_wrapper_member_base< C, A >, public metadata_handler<Metadata_Count>
{
    using accessor = A (C::*);
    public:
        property_wrapper(accessor acc, std::array<metadata, Metadata_Count> metadata_list)
        :   metadata_handler<Metadata_Count>(std::move(metadata_list)), property_wrapper_member_base< C, A >(acc)
        {
            static_assert(!std::is_pointer<A>::value, "The data type of the property is already a pointer type! The given policy cannot be used for this property.");
        }

        access_levels get_access_level() const { return Acc_Level; }
        bool is_readonly()  const   { return true; }
        bool is_static()    const   { return false; }
        type get_type()     const   { return type::get<typename std::add_const<A>::type*>(); }
        bool is_array()     const   { return detail::is_array<A>::value; }

        variant get_metadata(const variant& key) const { return metadata_handler<Metadata_Count>::get_metadata(key); }

        bool set_value(instance& object, argument& arg) const
        {
            return false;
        }

        variant get_value(instance& object) const
        {
            if (C* ptr = object.try_convert<C>())
                return variant(const_cast<const A*>(&(ptr->*m_acc)));
            else
                return variant();
        }

};

#endif // RTTR_PROPERTY_WRAPPER_MEMBER_OBJECT_H_
