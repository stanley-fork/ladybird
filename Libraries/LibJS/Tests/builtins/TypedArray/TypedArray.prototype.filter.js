const TYPED_ARRAYS = [
    Uint8Array,
    Uint8ClampedArray,
    Uint16Array,
    Uint32Array,
    Int8Array,
    Int16Array,
    Int32Array,
    Float16Array,
    Float32Array,
    Float64Array,
];

const BIGINT_TYPED_ARRAYS = [BigUint64Array, BigInt64Array];

test("length is 1", () => {
    TYPED_ARRAYS.forEach(T => {
        expect(T.prototype.filter).toHaveLength(1);
    });

    BIGINT_TYPED_ARRAYS.forEach(T => {
        expect(T.prototype.filter).toHaveLength(1);
    });
});

describe("errors", () => {
    function argumentErrorTests(T) {
        test(`requires at least one argument (${T.name})`, () => {
            expect(() => {
                new T().filter();
            }).toThrowWithMessage(
                TypeError,
                "TypedArray.prototype.filter() requires at least one argument"
            );
        });

        test(`callback must be a function (${T.name})`, () => {
            expect(() => {
                new T().filter(undefined);
            }).toThrowWithMessage(TypeError, "undefined is not a function");
        });

        test(`ArrayBuffer out of bounds (${T.name})`, () => {
            let arrayBuffer = new ArrayBuffer(T.BYTES_PER_ELEMENT * 2, {
                maxByteLength: T.BYTES_PER_ELEMENT * 4,
            });

            let typedArray = new T(arrayBuffer, T.BYTES_PER_ELEMENT, 1);
            arrayBuffer.resize(T.BYTES_PER_ELEMENT);

            expect(() => {
                typedArray.filter(value => value === 0);
            }).toThrowWithMessage(
                TypeError,
                "TypedArray contains a property which references a value at an index not contained within its buffer's bounds"
            );
        });
    }

    TYPED_ARRAYS.forEach(T => argumentErrorTests(T));
    BIGINT_TYPED_ARRAYS.forEach(T => argumentErrorTests(T));

    test("Symbol.species returns a typed array with a different content type", () => {
        TYPED_ARRAYS.forEach(T => {
            class TypedArray extends T {
                static get [Symbol.species]() {
                    return BigUint64Array;
                }
            }

            let result;

            expect(() => {
                result = new TypedArray().filter(() => {});
            }).toThrowWithMessage(TypeError, `Can't create BigUint64Array from ${T.name}`);

            expect(result).toBeUndefined();
        });

        BIGINT_TYPED_ARRAYS.forEach(T => {
            class TypedArray extends T {
                static get [Symbol.species]() {
                    return Uint32Array;
                }
            }

            let result;

            expect(() => {
                result = new TypedArray().filter(() => {});
            }).toThrowWithMessage(TypeError, `Can't create Uint32Array from ${T.name}`);

            expect(result).toBeUndefined();
        });
    });

    test("Symbol.species doesn't return a typed array", () => {
        TYPED_ARRAYS.forEach(T => {
            class TypedArray extends T {
                static get [Symbol.species]() {
                    return Array;
                }
            }

            let result;

            expect(() => {
                result = new TypedArray().filter(() => {});
            }).toThrowWithMessage(TypeError, "Not an object of type TypedArray");

            expect(result).toBeUndefined();
        });

        BIGINT_TYPED_ARRAYS.forEach(T => {
            class TypedArray extends T {
                static get [Symbol.species]() {
                    return Array;
                }
            }

            let result;

            expect(() => {
                result = new TypedArray().filter(() => {});
            }).toThrowWithMessage(TypeError, "Not an object of type TypedArray");

            expect(result).toBeUndefined();
        });
    });
});

describe("normal behavior", () => {
    test("never calls callback with empty array", () => {
        TYPED_ARRAYS.forEach(T => {
            let callbackCalled = 0;
            expect(
                new T([]).filter(() => {
                    callbackCalled++;
                })
            ).toHaveLength(0);
            expect(callbackCalled).toBe(0);
        });

        BIGINT_TYPED_ARRAYS.forEach(T => {
            let callbackCalled = 0;
            expect(
                new T([]).filter(() => {
                    callbackCalled++;
                })
            ).toHaveLength(0);
            expect(callbackCalled).toBe(0);
        });
    });

    test("calls callback once for every item", () => {
        TYPED_ARRAYS.forEach(T => {
            let callbackCalled = 0;
            expect(
                new T([1, 2, 3]).filter(() => {
                    callbackCalled++;
                })
            ).toHaveLength(0);
            expect(callbackCalled).toBe(3);
        });

        BIGINT_TYPED_ARRAYS.forEach(T => {
            let callbackCalled = 0;
            expect(
                new T([1n, 2n, 3n]).filter(() => {
                    callbackCalled++;
                })
            ).toHaveLength(0);
            expect(callbackCalled).toBe(3);
        });
    });

    test("can filter based on callback return value", () => {
        TYPED_ARRAYS.forEach(T => {
            const evenNumbers = new T([0, 1, 2, 3, 4, 5, 6, 7]).filter(x => x % 2 === 0);
            expect(evenNumbers).toHaveLength(4);
            expect(evenNumbers[0]).toBe(0);
            expect(evenNumbers[1]).toBe(2);
            expect(evenNumbers[2]).toBe(4);
            expect(evenNumbers[3]).toBe(6);
        });

        BIGINT_TYPED_ARRAYS.forEach(T => {
            const evenNumbers = new T([0n, 1n, 2n, 3n, 4n, 5n, 6n, 7n]).filter(x => x % 2n === 0n);
            expect(evenNumbers).toHaveLength(4);
            expect(evenNumbers[0]).toBe(0n);
            expect(evenNumbers[1]).toBe(2n);
            expect(evenNumbers[2]).toBe(4n);
            expect(evenNumbers[3]).toBe(6n);
        });
    });

    test("Symbol.species returns a typed array with a matching content type", () => {
        TYPED_ARRAYS.forEach(T => {
            class TypedArray extends T {
                static get [Symbol.species]() {
                    return Uint32Array;
                }
            }

            let result;

            expect(() => {
                result = new TypedArray([1, 2, 3]).filter(value => value % 2 === 0);
            }).not.toThrowWithMessage(TypeError, `Can't create Uint32Array from ${T.name}`);

            expect(result).toBeInstanceOf(Uint32Array);
            expect(result).toHaveLength(1);
            expect(result[0]).toBe(2);
        });

        BIGINT_TYPED_ARRAYS.forEach(T => {
            class TypedArray extends T {
                static get [Symbol.species]() {
                    return BigUint64Array;
                }
            }

            let result;

            expect(() => {
                result = new TypedArray([1n, 2n, 3n]).filter(value => value % 2n === 0n);
            }).not.toThrowWithMessage(TypeError, `Can't create BigUint64Array from ${T.name}`);

            expect(result).toBeInstanceOf(BigUint64Array);
            expect(result).toHaveLength(1);
            expect(result[0]).toBe(2n);
        });
    });
});
