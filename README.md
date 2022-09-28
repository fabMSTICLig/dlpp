# Dynamic Low Power Payload

This library is an attempt to implement a dynamic version of LPP for [RIOT-OS](https://github.com/RIOT-OS/RIOT) project.

## Principle

Creating a byte array containing a set number of integers of a particular type

| Channel | type\|number | byte N-1 | ... | byte 0 |
|---------|--------------|----------|-----|--------|

- The first byte is the Channel
- the second byte contain both the type of interger and the number of integer in the bytes array
- the following bytes are the data.

### Construct of the second byte

| 1 bit | 2-4 bit | 4-8 bit |
|-------|---------|---------|
| sign  | type    | number  |

- sign
  - 1 signed
  - 0 unsigned
- type
  - 1 int8
  - 2 int16
  - 4 int32
- number : number of integer [1-7]

Number of data bytes N = sign*type

## Usage
```
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
```


```
uint8_t buffer[(2+1*4)+(2+2*2)];
dlpp(CHANNEL_1, buffer,'I',1, (uint32_t)gas_resistance);
dlpp(CHANNEL_2, buffer+6,'h',2, (int16_t)temp, (int16_t)humidity);
```

For unpacking you can find a chirpstack decoder in the js folder.
