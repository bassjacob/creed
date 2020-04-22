open Higher;

type ordering =
  | LT
  | EQ
  | GT;

class virtual ord_ ('f) = {
  as self;
  pub virtual compare: 'a .(app('a, 'f), app('a, 'f)) => ordering;
  pub virtual lessThan: 'a .(app('a, 'f), app('a, 'f)) => bool;
  pub lessThan = (a, b) => LT == self#compare(a, b);
  pub virtual lessThanOrEqual: 'a .(app('a, 'f), app('a, 'f)) => bool;
  pub lessThanOrEqual = (a, b) =>
    switch (self#compare(a, b)) {
    | GT => false
    | _ => true
    };
  pub virtual greaterThan: 'a .(app('a, 'f), app('a, 'f)) => bool;
  pub greaterThan = (a, b) => GT == self#compare(a, b);
  pub virtual greaterThanOrEqual: 'a .(app('a, 'f), app('a, 'f)) => bool;
  pub greaterThanOrEqual = (a, b) =>
    switch (self#compare(a, b)) {
    | LT => false
    | _ => true
    };
  pub virtual max: 'a .(app('a, 'f), app('a, 'f)) => app('a, 'f);
  pub max = (a, b) => self#compare(a, b) == LT ? b : a;
  pub virtual min: 'a .(app('a, 'f), app('a, 'f)) => app('a, 'f);
  pub min = (a, b) => self#compare(a, b) == LT ? a : b;
};