#include "LyAmr.h"
#include "nortlib.h"

Circular::Circular() {
  max_size = 0;
  cur_size = 0;
  head = 0;
}

/**
 * Sets the size of the circular buffer
 * @return true if buffer was non-empty
 */
bool Circular::reinit(unsigned newsize) {
  bool rv = false;
  if (cur_size) {
    if (nl_response)
      nl_error(1, "Circular::reinit while non-empty");
    rv = true;
  }
  if (newsize > data.size()) {
    data.resize(newsize);
  }
  cur_size = 0;
  head = 0;
  max_size = newsize;
  return rv;
}

/**
 * This routine will ordinarily cause program termination if
 * an attempt is made to examine the first element while the
 * buffer is empty. This behavior can be modified through
 * set_response().
 * @return pointer to first sample in the buffer or NULL if empty
 *    and nl_response < 3.
 */
LyAmrSample *Circular::front() {
  if (!cur_size) {
    if (nl_response)
      nl_error(nl_response, "Circular::front() when empty");
    return 0;
  }
  return &data[head];
}

/**
 * By default, pop_front() will die if the buffer is empty.
 * This behavior can be changed via set_response().
 * @return true if buffer was empty
 */
bool Circular::pop_front() {
  if (!cur_size) {
    if (nl_response)
      nl_error(nl_response, "Circular::pop_front() when empty");
    return true;
  }
  if (++head >= max_size) head = 0;
  --cur_size;
  return false;
}

/**
 * By default, push_back() will die if the buffer was full.
 * This behavior can be changed via set_response().
 * @return true if buffer was full (and nl_response < 3)
 */
bool Circular::push_back(LyAmrSample S) {
  int tail = (head + cur_size) % max_size;
  if (cur_size == max_size) {
    if (nl_response)
      nl_error(nl_response, "Circular::push_back() when full");
    return true;
  }
  data[tail] = S;
  ++cur_size;
  return false;
}

bool Circular::full() {
  return cur_size >= max_size;
}

bool Circular::empty() {
  return cur_size == 0;
}
