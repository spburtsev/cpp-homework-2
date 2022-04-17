#include <cassert>
#include "VectorList.h"

int main() {
    const VectorList<int> check_const_compile;
    auto check_const_equals_compile = check_const_compile.begin();
    assert(check_const_equals_compile == check_const_equals_compile);

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