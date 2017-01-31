package com.projectpapa.SonicPi;

/**
 * Simple interface that just indicates the class can be converted into Sonic
 * Pi code.
 */
public interface Command {
    String toCode();
}