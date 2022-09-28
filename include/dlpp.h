#ifndef DLPP_H
#define DLPP_H

#ifdef __cplusplus
extern "C" {
#endif

#define DLPP_MAXSIZE 18

/**
 * @brief	Add a dlpp frame to a byte buffer
 *
 *
 * @param[in]   channel channel of the data
 * @param[in]   buffer buffer where to store the data
 * @param[in]   type type of integer possible values are ('b','B','h','H','i','I') following python pack format https://docs.python.org/fr/3/library/struct.html#format-characters
 * @param[in]   number number of integer added
 * @param[in]   ... the integers added 
 * @return  0 on success or negative for error
 */
int8_t dlpp(uint8_t channel, uint8_t * buffer, char type, uint8_t number, ...);

/**
 * @brief	Return the size of the dlpp frame including channel and type/number bytes
 *
 * @param[in]   buffer buffer where the data are stored
 * @return the size of the frame
 */
uint8_t dlpp_get_size(uint8_t * buffer);

#ifdef __cplusplus
}
#endif

#endif /* DLPP_H */

