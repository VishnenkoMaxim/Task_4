#include <iostream>
#include "version.h"
#include <vector>
#include <tuple>
#include<list>

//#include "spdlog/spdlog.h"

using namespace std;

/// \mainpage Task #4
///
/// \section intro_sec Introduction
///
/// This is the introduction
///

/// Template function to print IP with integral values
/// \tparam T       The type of value
/// \param value
/// \return         void
template <class T>
typename enable_if<is_integral<T>::value>::type
Print_IP(T value){
    uint8_t size = sizeof(value);
    uint8_t byte;
    for(short int i=size-1; i>=0; i--){
        byte = value >> 8*i;
        cout << (unsigned short int) byte;
        if (i!=0) cout << ".";
    }
    cout << endl;
}

/// Template function to print IP as a string
/// \tparam T The type of value (string)
/// \param value
/// \return  void
template <class T>
typename enable_if<is_same<T, string>::value, void>::type
Print_IP(T value){
    cout << value << endl;
}

/// Template function to print IP given as a container
/// \tparam Container might be list, vector, etc...
/// \tparam Type
/// \tparam Allocator
/// \param value
template <template <class, class> class Container, class Type, class Allocator = allocator<Type>,
typename = enable_if_t<is_same_v<Container<Type, Allocator>, list<Type, Allocator>> || is_same_v<Container<Type, Allocator>, vector<Type, Allocator>>>>
void Print_IP(const Container<Type, Allocator> &value){
    unsigned int i = 0;
    for(auto it = value.begin(); it != value.end(); it++){
        cout << *it;
        i++;
        if (i != value.size()) cout << ".";
    }
    cout << endl;
}

/// Template function to print IP given as a tuple
/// \tparam T tuple's elements type
/// \tparam Container must be tuple
/// \tparam T_elem type of first element
/// \param value tuple
template <class ... T, class T_elem = typename tuple_element<0, tuple<T...>>::type,
        class = enable_if_t<is_same_v<typename tuple_element<1, tuple<T...>>::type, T_elem>
                            && is_same_v<typename tuple_element<2, tuple<T...>>::type, T_elem>
                            && is_same_v<typename tuple_element<3, tuple<T...>>::type, T_elem>>>
void Print_IP(const tuple<T...> &value){
    cout << get<0>(value) << ".";
    cout << get<1>(value) << ".";
    cout << get<2>(value) << ".";
    cout << get<3>(value) << endl;
}

template <class T, size_t ... idx>
void PrintTuple(const T &_tuple, index_sequence<idx...>){
    size_t index = 0;
    size_t el_count = tuple_size<remove_reference_t<T>>::value;

    auto Print = [&index, &el_count] (const auto &value){
        cout << value;
        index++;
        if (index < el_count) cout << '.';
    };

    (Print(get<idx>(_tuple)), ...);
}

template <class ...T, size_t ... idx>
void Print_IP2(const tuple<T...> &value){
    PrintTuple(value, make_index_sequence<tuple_size<tuple<T...>>::value>{});
}

/// main function
/// \return
int main() {
    Print_IP(int8_t{-1});
    Print_IP(int16_t{0});
    Print_IP(int32_t{2130706433});
    Print_IP(int64_t{8875824491850138409});
    Print_IP(string{"Hello, World!"});
    Print_IP(vector<int> {100, 200, 300, 400});
    Print_IP(list<short> {400, 300, 200, 100});
    Print_IP(make_tuple(123, 456, 789, 0));
    Print_IP2(make_tuple(123, 456, 789, 0));

    return 0;
}
