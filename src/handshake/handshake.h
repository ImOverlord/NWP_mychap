/*
** EPITECH PROJECT, 2019
** NWP_mychap
** File description:
** handshake
*/

#ifndef HANDSHAKE_H_
#define HANDSHAKE_H_

#include "arguments/arguments.h"

#define ERROR_MSG       "Protocol Mismatch"
#define KO_MSG          "KO"
#define PHASE1_MESG     "client hello"
#define NONCE_LENGTH    10

int init_handshake(arguments_t **args);
char *sha256(const char *str);

#endif /* !HANDSHAKE_H_ */
