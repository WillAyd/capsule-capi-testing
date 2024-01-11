#include <nanobind/nanobind.h>
#include "nanoarrow/nanoarrow.h"

namespace nb = nanobind;

void some_function(nb::object table) {
  auto arrow_c_stream = nb::getattr(table, "__arrow_c_stream__")();
  PyObject *obj = arrow_c_stream.ptr();
  if (!PyCapsule_CheckExact(obj)) {
    throw std::invalid_argument("Object does not provide capsule");
  }

  auto stream = static_cast<struct ArrowArrayStream*>(PyCapsule_GetPointer(obj, "arrow_array_stream"));
  struct ArrowSchema schema;
  if (!stream->get_schema(stream, &schema)) {
    //std::string errMsg{stream->get_last_error(stream)};
    throw std::runtime_error("Could not read from arrow schema:");
  }
}

NB_MODULE(somelib, m) {
  m.def("some_function", &some_function, nb::arg("table"));
}
