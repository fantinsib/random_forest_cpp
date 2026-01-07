# 🌳 treelib — Experimental Random Forest in C++


This repository contains a small, experimental implementation of a Random Forest engine written in C++, with Python bindings.

The project is intended mainly for **learning and experimentation**, rather than production use. An upgraded version can be found in the [arboria project](https://github.com/fantinsib/arboria)(WIP). Feel free to check it!

---

## Installation

```bash 
git clone https://github.com/fantinsib/random_forest_cpp.git
cd random_forest_cpp
pip install -e .
```

## Quick Usage

```python
from treelib import RandomForest
n_trees = 100
m_try = 10
rf = RandomForest(n_trees, m_try)
```

Please see the [demo notebook](https://github.com/fantinsib/random_forest_cpp/blob/main/demo_random_forest.ipynb) for a quick demonstration !

## Notes

• Data is internally stored as 1D contiguous arrays

• Tree construction follows standard CART-style splits (Gini)

• Random Forest uses bootstrap sampling and random feature subsampling (m_try)
