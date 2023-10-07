#pragma once



namespace pl::utils
{
	struct KeyState
	{
		bool isDown;
		bool hasChanged;
	};


	using SDL2_Scancode = size_t;
	size_t convertSDL2KeysToPL(pl::utils::SDL2_Scancode key);


	namespace keys
	{
		inline size_t a {0},
			b {1},
			c {2},
			d {3},
			e {4},
			f {5},
			g {6},
			h {7},
			i {8},
			j {9},
			k {10},
			l {11},
			m {12},
			n {13},
			o {14},
			p {15},
			q {16},
			r {17},
			s {18},
			t {19},
			u {20},
			v {21},
			w {22},
			x {23},
			y {24},
			z {25},
			escape {26},
			space {27},
			left {28},
			right {29},
			up {30},
			down {31},
			k1 {32},
			k2 {33},
			k3 {34},
			k4 {35},
			k5 {36},
			k6 {37},
			k7 {38},
			k8 {39},
			k9 {40},
			k0 {41},
			unknown {42};
	}

	
} // namespace pl::utils
