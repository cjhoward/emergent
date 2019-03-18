# Coding Style Guide

## Class and Data Type Names

POD data types and containers that are considered to be an integral part of the software should be named in all lowercase, such as in the C++ Standard Template Library.

	using float3 = std::array<float, 3>;
	using int4x2 = std::array<std::array<int, 2>, 4>;

Non-POD classes which are not an integral part of the software should start with an uppercase letter, with each successive word beginning with an uppercase letter as well. Abbreviations should be all uppercase.

	class StateMachine; // State machine
	class FSMState;     // FSM (Finite-State Machine) state

## Variable Names

All variable names should be in camelcase, with the first word in all lowercase. Abbreviations should maintain the same case.

	int layerIndexOffset = -1;
	int ibo = 3; // IBO (Index Buffer Object)
	int modelVBIndex // model VB (Vertex Buffer) index

## Operators

All standard binary arithmetic operators should be preceeded and follow by exactly one space.

	float3 v3 = v1 + v2 * 2.0f / (4.0f - 1.0f);
	int state = a % 10 + (5 << 3);
