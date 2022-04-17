#include <vector>
#include <list>
#include <cstddef>
#include <cassert>

template<class T>
struct VectorList {
    using VectT = std::vector<T>;
    using ListT = std::list<VectT>;
    ListT data_;

    VectorList() = default;

    VectorList(VectorList const &) = default;

    VectorList(VectorList &&) noexcept = default;

    VectorList &operator=(VectorList &&) noexcept = default;

    VectorList &operator=(VectorList const &) = default;

    template<class It>
    void append(It p, It q);

    bool empty() const { return size() == 0; }

    size_t size() const {
        size_t sz = 0;
        for (auto const &v: data_)
            sz += v.size();
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

template<class T>
template<class It>
void VectorList<T>::append(It p, It q) {
    if (p != q)
        data_.push_back(VectT(p, q));
}

int main() {
    const VectorList<int> check_const_compile;
    auto check_const_equals_compile = check_const_compile.begin();
    check_const_equals_compile == check_const_equals_compile;

    VectorList<std::vector<int>> check_arrow_vl;
    std::vector<int> vint1 = {1, 2, 3};
    std::vector<int> vint2 = {4, 5, 6};
    std::vector<std::vector<int>> vecs;
    vecs.push_back(vint1);
    vecs.push_back(vint2);
    check_arrow_vl.append(vecs.begin(), vecs.end());
    auto it_f = check_arrow_vl.begin();
    assert(it_f->size() == 3);

    VectorList<char> vec_list;

    std::vector<char> v1;
    v1.push_back('A');
    v1.push_back('B');
    v1.push_back('C');
    vec_list.append(v1.begin(), v1.end());

    std::vector<char> v2;
    v2.push_back('D');
    v2.push_back('E');
    v2.push_back('F');
    v2.push_back('G');
    vec_list.append(v2.begin(), v2.end());

    assert(vec_list.size() == 7);
    assert(std::distance(vec_list.begin(), vec_list.end()) == 7);

    auto it = vec_list.begin();
    assert(*it == 'A');
    ++it;
    assert(*it == 'B');
    ++it;
    assert(*it == 'C');
    ++it;
    assert(*it == 'D');
    ++it;
    assert(*it == 'E');
    ++it;
    assert(*it == 'F');
    ++it;
    assert(*it == 'G');
    ++it;
    assert(it == vec_list.end());

    it = vec_list.begin();
    assert(*it == 'A');
    it++;
    assert(*it == 'B');
    it++;
    assert(*it == 'C');
    it++;
    assert(*it == 'D');
    it++;
    assert(*it == 'E');
    it++;
    assert(*it == 'F');
    it++;
    assert(*it == 'G');
    it++;

    it = vec_list.end();
    it--;
    assert(*it == 'G');
    it--;
    assert(*it == 'F');
    it--;
    assert(*it == 'E');
    it--;
    assert(*it == 'D');
    it--;
    assert(*it == 'C');
    it--;
    assert(*it == 'B');
    it--;
    assert(*it == 'A');

    it = vec_list.end();
    --it;
    assert(*it == 'G');
    --it;
    assert(*it == 'F');
    --it;
    assert(*it == 'E');
    --it;
    assert(*it == 'D');
    --it;
    assert(*it == 'C');
    --it;
    assert(*it == 'B');
    --it;
    assert(*it == 'A');

    auto r_it = vec_list.rbegin();
    assert(*r_it == 'G');
    r_it++;
    assert(*r_it == 'F');
    r_it++;
    assert(*r_it == 'E');
    r_it++;
    assert(*r_it == 'D');
    r_it++;
    assert(*r_it == 'C');
    r_it++;
    assert(*r_it == 'B');
    r_it++;
    assert(*r_it == 'A');
    r_it++;
    assert(r_it == vec_list.rend());

    r_it = vec_list.rbegin();
    assert(*r_it == 'G');
    ++r_it;
    assert(*r_it == 'F');
    ++r_it;
    assert(*r_it == 'E');
    ++r_it;
    assert(*r_it == 'D');
    ++r_it;
    assert(*r_it == 'C');
    ++r_it;
    assert(*r_it == 'B');
    ++r_it;
    assert(*r_it == 'A');
    ++r_it;
    assert(r_it == vec_list.rend());

    r_it = vec_list.rend();
    --r_it;
    assert(*r_it == 'A');
    --r_it;
    assert(*r_it == 'B');
    --r_it;
    assert(*r_it == 'C');
    --r_it;
    assert(*r_it == 'D');
    --r_it;
    assert(*r_it == 'E');
    --r_it;
    assert(*r_it == 'F');
    --r_it;
    assert(*r_it == 'G');

    r_it = vec_list.rend();
    r_it--;
    assert(*r_it == 'A');
    r_it--;
    assert(*r_it == 'B');
    r_it--;
    assert(*r_it == 'C');
    r_it--;
    assert(*r_it == 'D');
    r_it--;
    assert(*r_it == 'E');
    r_it--;
    assert(*r_it == 'F');
    r_it--;
    assert(*r_it == 'G');

    VectorList<int> check_empty;
    assert(check_empty.size() == 0);
    assert(check_empty.empty());
    assert(check_empty.begin() == check_empty.end());
    assert(check_empty.rbegin() == check_empty.rend());

    return 0;

    return 0;
}