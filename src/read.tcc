#pragma once

#include "defs.h"
#include "tuple.tcc"
#include "array.tcc"
#include <PString.h>
#include <TString.tcc>

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

#define MAX_SIZE 128

//! \defgroup read

/*! \ingroup read
 * Read a value from an stream.
 *
 * \param io Stream.
 * \param data Data.
 */
template <class T>
void rpcRead(Stream& io, T* data) {
  io.readBytes(reinterpret_cast<char*>(data), sizeof(T));
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
inline void rpcRead(Stream& io, T const* data) {
  rpcRead(io, const_cast<T*>(data));
}

inline void rpcRead(Stream& io, char** data) {
    static char buffer[MAX_PTR_SIZE];
    char character;
    size_t size = 0;

    // Read characters into buffer until null terminator or max size reached
    do {
        rpcRead(io, &character);
        if (size < MAX_PTR_SIZE - 1) {  // Leave space for null terminator
            buffer[size++] = character;
        } else {
            break;
        }
    } while (character != '\0');

    buffer[size] = '\0';  // Ensure buffer is null-terminated
    *data = buffer;

    // empty the stream to avoid blocking
    while (character != '\0') {
        rpcRead(io, &character);
    }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, char const** data) {
  rpcRead(io, const_cast<char**>(data));
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, String* data) {
  char character;

  rpcRead(io, &character);

  while (character) {
    *data += character;
    rpcRead(io, &character);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template<size_t S>
inline void rpcRead(Stream& io, TString<S>* data) {
  char character;
  rpcRead(io, &character);

  while (character) {
    *data += character;
    rpcRead(io, &character);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, PString* data) {
  char character;
  rpcRead(io, &character);

  while (character) {
    *data += character;
    rpcRead(io, &character);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, T** data) {
    static T buffer[MAX_PTR_SIZE];               // Fixed-size buffer

    size_t size;
    rpcRead(io, &size);

    size_t readSize = (size < MAX_PTR_SIZE) ? size : MAX_PTR_SIZE;

    for (size_t i = 0; i < readSize; ++i) {
        rpcRead(io, &buffer[i]);
    }

    // Discard extra data beyond MAX_SIZE, if any
    T discard;
    for (size_t i = readSize; i < size; ++i) {
        rpcRead(io, &discard);
    }

    *data = buffer;  // Set the data pointer to the static buffer
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T, size_t n>
void rpcRead(Stream& io, Array<T, n>* data) {
  size_t size;
  rpcRead(io, &size);

  for (size_t i = 0; i < min(size, n); ++i) {
    rpcRead(io, &(*data)[i]);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, T const** data) {
  rpcRead(io, const_cast<T**>(data));
}

template <class T>
void rpcRead(Stream& io, T*** data) {
    static T* buffer[MAX_PTR_SIZE + 1];          // Fixed-size buffer with space for nullptr terminator

    size_t size;
    rpcRead(io, &size);

    size_t readSize = (size < MAX_PTR_SIZE) ? size : MAX_PTR_SIZE;

    // Read up to the fixed buffer limit
    for (size_t i = 0; i < readSize; ++i) {
        rpcRead(io, &buffer[i]);
    }
    buffer[readSize] = nullptr;  // Set nullptr terminator

    // Discard extra data beyond MAX_SIZE if any
    T* discard;
    for (size_t i = readSize; i < size; ++i) {
        rpcRead(io, &discard);
    }

    *data = buffer;  // Set the data pointer to the static buffer
}


//! Recursion terminator for `rpcRead(Tuple*)`.
inline void rpcRead(Stream&, Tuple<>*) {}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class... Ts>
void rpcRead(Stream& io, Tuple<Ts...>* data) {
  rpcRead(io, &(*data).head);
  rpcRead(io, &(*data).tail);
}
