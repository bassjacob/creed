open Higher;

class virtual num ('n) = {
  as _;
  pub virtual add: 'a .(app('a, 'n), app('a, 'n)) => app('a, 'n);
  pub virtual subtract: 'a .(app('a, 'n), app('a, 'n)) => app('a, 'n);
  pub virtual multiply: 'a .(app('a, 'n), app('a, 'n)) => app('a, 'n);
  pub virtual negate: 'a .app('a, 'n) => app('a, 'n);
};