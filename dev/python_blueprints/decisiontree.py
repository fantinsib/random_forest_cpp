from dataclasses import dataclass
import numpy as np
from typing import Optional, Any

@dataclass
class Node:
    feature: Optional[int]= None
    threshold: Optional[float] = None
    id: Optional[int] = None
    left: Optional["Node"] = None
    right: Optional["Node"] = None

class TypeError(Exception):
    pass

class DecisionTree:

    def __init__(self, max_depth= 5, min_sample_split= 2, min_impurity_decrease=0.0):
        self.max_depth = max_depth
        self.min_sample_split = min_sample_split
        self.min_impurity_decrease = min_impurity_decrease
        self.root = None
        self._next_id = 1 

    def _best_split(self, X, y):

        X = np.asarray(X)
        y = np.asarray(y)
        if X.ndim != 2: raise TypeError
        if y.ndim != 1: raise TypeError
        if X.shape[0] != y.shape[0]: raise ValueError

        n_samples = X.shape[0]
        n_features = X.shape[1]

        optimal_mask = []
        best_split = 100

        for f in range(n_features):
            print(f)
            values = np.unique(X[:,f])
            if values.size <= 1: continue
             #prends le midpoints entre chaque valeur unique consécutive
            threshold = (values[:-1]+values[1:])/2
            
            for val in threshold:

                mask = X[:, f] < val

                if mask.sum() == 0 or mask.sum()==n_samples: continue
                x_left, x_right = X[mask], X[~mask]
                y_left, y_right = y[mask], y[~mask]
                left_gini, right_gini = (self.gini_score(y_left), self.gini_score(y_right))
                weighted_split = (len(y_left)/n_samples) *left_gini + (len(y_right)/n_samples)*right_gini
                
                if weighted_split < best_split: 
                    best_split = weighted_split
                    optimal_mask = mask
                    best_feature = f
                    best_threshold = val

        node = Node(feature=best_feature, threshold=best_threshold, id = 1)
        if best_feature is None:
            return None, None, None, None, None
        
        x_left_child, x_right_child = X[optimal_mask], X[~optimal_mask]
        y_left_child, y_right_child = y[optimal_mask], y[~optimal_mask]
        

        return node, x_left_child, x_right_child, y_left_child, y_right_child

    def fit(self):


        

    def gini_score(self, y):

        _, count = np.unique(y, return_counts = True)
        return 1 - sum((n/count.sum())**2 for n in count)

        


