#ifndef DLPP_H
#define DLPP_H

#ifdef __cplusplus
extern "C" {
#endif

#define DLPP_MAXSIZE 18

int8_t dlpp(uint8_t channel, uint8_t * buffer, char type, uint8_t number, ...);
uint8_t dlpp_get_size(uint8_t * buffer);

#ifdef __cplusplus
}
#endif

#endif /* DLPP_H */

