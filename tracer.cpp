#include <pybind11/functional.h>
#include <pybind11/pybind11.h>

#include <iostream>

namespace py = pybind11;

class Tracer {
   public:
    Tracer() : tracing(false) {}

    void start() {
        if (!tracing) {
            py::module sys = py::module::import("sys");
            sys.attr("settrace")(py::cpp_function(&Tracer::trace_callback));
            tracing = true;
        }
    }

    void stop() {
        if (tracing) {
            py::module sys = py::module::import("sys");
            sys.attr("settrace")(py::none());
            tracing = false;
        }
    }

   private:
    static void trace_callback(py::object frame, const std::string& event,
                               py::object arg) {
        if (event == "call") {
            py::object code = frame.attr("f_code");
            std::string filename = py::str(code.attr("co_filename"));
            int lineno = py::int_(code.attr("co_firstlineno"));
            std::string func_name = py::str(code.attr("co_name"));
            std::cout << "Call to " << func_name << " in " << filename << ":"
                      << lineno << std::endl;
        }
    }

    bool tracing;
};

PYBIND11_MODULE(tracer, m) {
    py::class_<Tracer>(m, "Tracer")
        .def(py::init<>())
        .def("start", &Tracer::start)
        .def("stop", &Tracer::stop);
}
