open Higher;

class virtual eq_ ('f) = {
  as self;
  pub virtual equal: 'a .(app('a, 'f), app('a, 'f)) => bool;
  pub virtual notEqual: 'a .(app('a, 'f), app('a, 'f)) => bool;
  pub notEqual = (a, b) => self#equal(a, b) |> (!);
};