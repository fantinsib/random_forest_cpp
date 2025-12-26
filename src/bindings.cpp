#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <stdexcept>

#include <myforest/decisiontree.h>
#include <myforest/randomforest.h>
#include <myforest/dataset.h>


namespace py = pybind11;

PYBIND11_MODULE(_treelib, m) {


    py::class_<myforest::RandomForest>(m, "RandomForest")
        .def(py::init<int, int>())
        .def("fit", 
        [](myforest::RandomForest& self, 
         py::array_t<float, py::array::c_style | py::array::forcecast> X,
        py::array_t<float, py::array::c_style | py::array::forcecast> y)
        {
                auto xb = X.request();
                if (xb.ndim != 2) {
                    throw std::runtime_error("X must be a 2D numpy array.");
                }
                auto yb = y.request();
                if (yb.ndim != 1) {
                    throw std::runtime_error("y must be a 1D numpy array.");
                }
                const int n_rows = static_cast<int>(xb.shape[0]);
                const int n_cols = static_cast<int>(xb.shape[1]);
                if ((int)yb.shape[0] != n_rows) {
                    throw std::runtime_error("y length must match X.shape[0].");
                }
                
                const float* X_ptr = static_cast<const float*>(xb.ptr);
                const float* y_ptr = static_cast<const float*>(yb.ptr);

                std::vector<float> X_vec(X_ptr, X_ptr + n_rows * n_cols);
                std::vector<float> y_vec(y_ptr, y_ptr + n_rows);

                myforest::DataSet data(X_vec, y_vec, n_rows, n_cols);
                self.fit(data);
            },
            py::arg("X"), py::arg("y")
        )

        .def("predict", 
        [](myforest::RandomForest& self, 
        py::array_t<float, py::array::c_style | py::array::forcecast> X)
        {
            auto xb = X.request();
            if (xb.ndim != 2) throw std::runtime_error("X must be a 2D numpy array.");
            const int n_rows = static_cast<int>(xb.shape[0]);
            const int n_cols = static_cast<int>(xb.shape[1]);

            const float* x_ptr = static_cast<const float*>(xb.ptr);

            std::vector<float> X_vec(x_ptr, x_ptr+n_rows*n_cols);

            return self.predict(X_vec);
        }
    );
}