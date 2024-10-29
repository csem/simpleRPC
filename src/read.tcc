#pragma once

#include "defs.h"
#include "tuple.tcc"
#include "array.tcc"
#include <PString.h>
#include <TString.tcc>

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

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

//! Recursion terminator for `rpcRead(Tuple*)`.
inline void rpcRead(Stream&, Tuple<>*) {}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class... Ts>
void rpcRead(Stream& io, Tuple<Ts...>* data) {
  rpcRead(io, &(*data).head);
  rpcRead(io, &(*data).tail);
}
