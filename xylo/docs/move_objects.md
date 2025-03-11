# Move Objects

Differs from C++, assignments in XY that use an object-typed expression as
RHS will move the object on the RHS.

For example:

```xy
let a: object_t;
let b: object_t = a;
let c: object_t = object_t {
    test: 123
};

c = b;
```

In this case the object stored in `a` will be moved to `b` and the `a` will be
nullified (by the `this` method), and then `c` will be initialized with our
specified object, finally we use `b` to overwrite data of `c`, the object
previously in `c` will be released and the `b` will be nullified due to the
move of the object, the `this=` method will also be called.
