/////////////////////////////////////////////////////////////////////////////
/// @file string_collection.h
/// Definition of the string_collection class for the Paho MQTT C++ library.
/// @date April 23, 2017
/// @author Frank Pagliughi
/////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
 * Copyright (c) 2017 Frank Pagliughi <fpagliughi@mindspring.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Frank Pagliughi - initial implementation and documentation
 *******************************************************************************/

#ifndef __mqtt_string_collection_h
#define __mqtt_string_collection_h

#include "mqtt/types.h"
#include <vector>
#include <memory>

namespace mqtt {

/////////////////////////////////////////////////////////////////////////////

/**
 * Type for a collection of topics.
 * This acts like a collection of strings but carries an array of pointers
 * to the C strings for easy interactions with the Paho C library.
 */
class string_collection
{
	/** The type for the collection of strings */
	using collection_type = std::vector<string>;
	/** The type for the array of C pointers */
	using c_arr_type = std::vector<const char*>;

	/**
	 * The collection of strings for the topics.
	 */
	collection_type coll_;
	/**
	 * A colleciton of pointers to NUL-terminated C strings for the topics.
	 * This is what is required by the Paho C library, and thus the lifetime
	 * of the pointers will remain consistent with the lifetime of the
	 * object. The value is kept consistent with the current topics and
	 * updated whenever topics are added or removed.
	 */
	c_arr_type cArr_;
	/**
	 * Updated the cArr_ object to agree with the values in coll_ 
	 * This should be called any time the coll_ variable is modified 
	 * <i>in any way</i>. 
	 */
	void update_c_arr();

public:
	/** Smart/shared pointer to an object of this type */
	using ptr_t = std::shared_ptr<string_collection>;
	/** Smart/shared pointer to a const object of this type */
	using const_ptr_t = std::shared_ptr<const string_collection>;

	string_collection() =default;
	string_collection(const string& str);
	string_collection(string&& str);
	string_collection(const collection_type& vec);
	string_collection(collection_type&& vec);
	string_collection(const string_collection& coll);
	string_collection(string_collection&& coll) = default;
	string_collection(std::initializer_list<string> sl);
	string_collection(std::initializer_list<const char*> sl);

	static ptr_t create(const string& str) {
		return std::make_shared<string_collection>(str);
	}

	static ptr_t create(string&& str) {
		return std::make_shared<string_collection>(str);
	}

	static ptr_t create(const collection_type& vec) {
		return std::make_shared<string_collection>(vec);
	}

	static ptr_t create(collection_type&& vec) {
		return std::make_shared<string_collection>(vec);
	}

	static ptr_t create(std::initializer_list<string> sl) {
		return std::make_shared<string_collection>(sl);
	}

	static ptr_t create(std::initializer_list<const char*> sl) {
		return std::make_shared<string_collection>(sl);
	}

	string_collection& operator=(const string_collection& coll);
	string_collection& operator=(string_collection&& coll) = default;

	size_t empty() const { return coll_.empty(); }
	size_t size() const { return coll_.size(); }

	void push_back(const string& str);
	void push_back(string&& str);

	void clear();

	string operator[](size_t i) { return coll_[i]; }
	const string& operator[](size_t i) const { return coll_[i]; }

	/**
	 * Gets a pointer to an array of NUL-terminated C string pointers.
	 * This is the collection type supported by the underlying Paho C
	 * library. The returned pointer is guaranteed valid so long as the
	 * object is not updated. The return value may change if the object is
	 * modified, so the application should not cache the return value, but
	 * rather request the value when needed.
	 * @return pointer to an array of NUL-terminated C string pointers of
	 *  	   the topics in the object.
	 *
	 */
	char* const* c_arr() const { return (char* const *) cArr_.data(); }
	//const char* const* c_arr() const { return cArr_.data(); }
};

/////////////////////////////////////////////////////////////////////////////

/** Smart/shared pointer to a topic collection */
using string_collection_ptr = string_collection::ptr_t;

/** Smart/shared pointer to a const string_collection */
using const_string_collection_ptr = string_collection::const_ptr_t;

/////////////////////////////////////////////////////////////////////////////
// end namespace mqtt
}

#endif		// __mqtt_string_collection_h

