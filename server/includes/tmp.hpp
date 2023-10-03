/*
** EPITECH PROJECT, 2023
** server
** File description:
** test
*/

#ifndef TEST_HPP_
#define TEST_HPP_

#include <vector>

// public:
//     struct Components_iterator
//     {
//     public:
//         Components_iterator(pointer_type ptr, pointer_type end_ptr = 0) : m_ptr(ptr), _end_ptr(end_ptr) {}

//         reference_type operator*() const { return *m_ptr; }

//         pointer_type operator->() { return m_ptr; }

//         // Prefix increment
//         Components_iterator &operator++()
//         {
//             m_ptr++;
//             _iterations++;
//             while (m_ptr != _end_ptr && !m_ptr->has_value()) {
//                 m_ptr++;
//                 _iterations++;
//             }
//             return *this;
//         }

//         size_t get_entity()
//         {
//             return _iterations;
//         }

//         // Postfix increment
//         Components_iterator operator++(int)
//         {
//             Components_iterator tmp = *this;

//             ++(*this);
//             ++_iterations;
//             while (m_ptr != _end_ptr && !this->m_ptr->has_value()) {
//                 ++(*this);
//                 ++_iterations;
//             }
//             return tmp;
//         }

//         friend bool operator==(const Components_iterator &a, const Components_iterator &b) { return a.m_ptr == b.m_ptr; };
//         friend bool operator!=(const Components_iterator &a, const Components_iterator &b) { return a.m_ptr != b.m_ptr; };

//     private:
//         pointer_type m_ptr;
//         pointer_type _end_ptr;
//         size_t _iterations = 0;
//     };

    // using iterator = sparse_array<Component>::Components_iterator;


#endif /* !TEST_HPP_ */
