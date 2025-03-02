# C FFI Compatibility in XY

The function name will be mangled if a function:
* is a member function.

If a function is a member function, the first parameter will be a pointer to `this`.

If a function has an object return type, the last parameter will be a pointer to where the object will be stored.
