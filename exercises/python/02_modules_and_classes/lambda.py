#!/usr/bin/env python3
# -*- coding: utf-8 -*-

lista = ["hola", "adios", "la_vin_compae", "Trst", "Glemone_Friûl"]
lista.append("a")
lista.append("z")

new_lista = sorted(lista, key = lambda word : word[len(word)-1:0:-1] + word[0])
print(new_lista)

