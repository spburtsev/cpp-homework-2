#ifndef UNTITLED_VECTORLIST_H
#define UNTITLED_VECTORLIST_H

#include <vector>
#include <list>
#include <cstddef>

template<class T>
class VectorList {
private:
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;
    ListT data_;

public:
    VectorList() = default;

    VectorList(VectorList const &) = default;

    VectorList(VectorList &&) noexcept = default;

    VectorList &operator=(VectorList &&) noexcept = default;

    VectorList &operator=(VectorList const &) = default;

    template<class It>
    void append(It p, It q) {
        if (p != q) {
            data_.push_back(VectT(p, q));
        }
    }

    inline bool empty() const { return size() == 0; }

    inline size_t size() const {
        size_t sz = 0;
        for (auto const &v: data_) {
            sz += v.size();
        }
        return sz;
    }

    struct const_iterator
            : std::iterator<std::bidirectional_iterator_tag, const T> {
        typename ListT::const_iterator itl;
        typename VectT::const_iterator itv;
        ListT const *data = nullptr;

        const_iterator(ListT const *data, typename ListT::const_iterator itl,
                       typename VectT::const_iterator itv)
                : itl(itl), itv(itv), data(data) {}

        const_iterator(ListT const *data, typename ListT::const_iterator itl)
                : itl(itl), data(data) {
            if (itl != data->end())
                itv = itl->begin();
            else
                itv = itl->end();
        }

        explicit const_iterator(ListT const *data)
                : data(data) {
            itl = data->end();
            --itl;
            itv = itl->end();
        }

        const_iterator() = default;

        const_iterator &operator++() {
            ++itv;
            if (itv == itl->end()) {
                ++itl;
                if (itl != data->end())
                    itv = itl->begin();
                else {
                    *this = const_iterator(data);
                }
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++*this;
            return tmp;
        }

        const_iterator &operator--() {
            if (itv != itl->begin()) {
                --itv;
            } else {
                --itl;
                itv = itl->end();
                --itv;
            }
            return *this;
        }

        const_iterator operator--(int) {
            const_iterator tmp = *this;
            --*this;
            return tmp;
        }

        bool operator==(const_iterator const &other) const {
            return itl == other.itl && itv == other.itv;
        }

        bool operator!=(const_iterator const &other) const {
            return itl != other.itl || itv != other.itv;
        }

        T const &operator*() const { return *itv; }

        T const *operator->() const { return &*itv; }

    };

    const_iterator begin() const {
        return const_iterator(&data_, data_.begin());
    }


    const_iterator end() const {
        return const_iterator(&data_);
    }

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }
};


#endif //UNTITLED_VECTORLIST_H
