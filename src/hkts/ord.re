open Higher;

type ordering = LT | LTE | EQ | GTE | GT;

class virtual ord_ 'f = {
  as _;
  pub virtual compare: 'a. (app 'a 'f) => (app 'a 'f) => ordering;
  pub virtual lessThan: 'a. (app 'a 'f) => (app 'a 'f) => bool;
  pub virtual lessThanOrEqual: 'a. (app 'a 'f) => (app 'a 'f) => bool;
  pub virtual greaterThan: 'a. (app 'a 'f) => (app 'a 'f) => bool;
  pub virtual greaterThanOrEqual: 'a. (app 'a 'f) => (app 'a 'f) => bool;
  pub virtual max: 'a. (app 'a 'f) => (app 'a 'f) => (app 'a 'f);
  pub virtual min: 'a. (app 'a 'f) => (app 'a 'f) => (app 'a 'f);
};
