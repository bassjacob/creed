open Higher;

class virtual eq_ 'f = {
  as _;
  pub virtual equal: 'a. (app 'a 'f) => (app 'a 'f) => bool;
  pub virtual notEqual: 'a. (app 'a 'f) => (app 'a 'f) => bool;
};
