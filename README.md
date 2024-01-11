install cmake, nanobind

cmake -S . -B build
cmake --build build
cd build
python

```python
import pyarrow as pa
import somelib

tbl = pa.Table.from_pydict({"col": [1, 2, 3]})
somelib.some_function(tbl)
```