#pragma once

#include "print.tcc"
#include "tuple.tcc"
#include "vector.tcc"
#include "array.tcc"
#include "rolling_buffer.tcc"
#include <PString.h>
#include <TString.tcc>

//! \defgroup write


/*! \ingroup write
 * Write a value to a stream.
 *
 * \param io Stream.
 * \param data Data.
 */
template <class T>
void rpcWrite(Stream& io, T* data) {
  io.write(reinterpret_cast<uint8_t*>(data), sizeof(T));
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, char** data) {
  rpcPrint(io, *data, '\0');
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, char const** data) {
  rpcWrite(io, const_cast<char**>(data));
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, String* data) {
  rpcPrint(io, *data, '\0');
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, PString* data)
{
  const char* str = *data;
  rpcPrint(io, str);
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template<size_t S>
inline void rpcWrite(Stream& io, TString<S>* data)
{
  const char* str = *data;
  rpcPrint(io, str);
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class T>
void rpcWrite(Stream& io, Vector<T>* data) {
  size_t size {(*data).size()};
  rpcWrite(io, &size);
  for (size_t i {0}; i < size; ++i) {
    rpcWrite(io, &(*data)[i]);
  }
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class T, size_t n>
void rpcWrite(Stream& io, Array<T, n>* data) {
  size_t size {(*data).size()};
  rpcWrite(io, &size);
  for (size_t i {0}; i < size; ++i) {
    rpcWrite(io, &(*data)[i]);
  }
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class T, size_t S>
void rpcWrite(Stream& io, RollingBuffer<T, S>* data)
{
  size_t size = data->begin_read();
  rpcWrite(io, &size);
  for (size_t i = 0; i < size; i++)
  {
    rpcWrite(io, (T*)data->pop());
  }
  data->end_read();
}

//! Recursion terminator for `rpcWrite(Tuple*)()`.
inline void rpcWrite(Stream&, Tuple<>*) {}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class... Ts>
void rpcWrite(Stream& io, Tuple<Ts...>* data) {
  rpcWrite(io, &(*data).head);
  rpcWrite(io, &(*data).tail);
}
