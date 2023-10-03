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
        zipper(Containers &...cs);
        iterator begin();
        iterator end();

    private:
        // helper function to know the maximum index of our iterators .
        static size_t _compute_size(Containers &...containers);
        // helper function to compute an iterator_tuple that will allow us to
        // build our end iterator.
        static iterator_tuple _compute_end(Containers &...containers);

    private:
        iterator_tuple _begin;
        iterator_tuple _end;
        size_t _size;
    };
}

#endif /* !ZIPPER_HPP_ */
