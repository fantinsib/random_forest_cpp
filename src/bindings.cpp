#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(treelib, m) {
    m.doc() = "C++ Decision Tree / Random Forest library";
    m.doc() = "myforest bindings";
    m.def("ping", [](){ return "pong"; });

    m.def("echo_int", [](int x) { return x; }, "Return the same integer");

}
