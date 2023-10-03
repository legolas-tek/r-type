/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** zipper
*/

#ifndef ZIPPER_HPP_
#define ZIPPER_HPP_

namespace containers {

    template <class... Containers>
    class zipper_iterator;

    template <class... Containers>
    class zipper
    {
    public:
        using iterator = zipper_iterator<Containers...>;
        using iterator_tuple = typename iterator::iterator_tuple;

        zipper(Containers &... cs) :
            _begin(cs.begin()...),
            _end(_compute_end(cs...)),
            _size(_compute_size(cs...))
        {}

        iterator begin() {
            return iterator(_begin, _size);
        }

        iterator end() {
            return iterator(_end, _size);
        }

    private:
        static size_t _compute_size(Containers &... containers) {
            return std::min({containers.size()...});
        }

        static iterator_tuple _compute_end(Containers &... containers) {
            return iterator_tuple(containers.end()...);
        }

    private:
        iterator_tuple _begin;
        iterator_tuple _end;
        size_t _size;
    };
};

#endif /* !ZIPPER_HPP_ */
