//! Responsible for procedural generation for the world.
//!
//! This will inevitably become more complex with future updates, and the code involved is subject 
//! to change with the game design.

use block;
use world::chunk;
use std;
use world;
use rand;

const DEFAULT_DEPTH: usize = (std::u8::MAX as usize) / 2;
const LIMIT: usize = 100;

struct DepthPoint {
	pub x: usize,
	pub chunk: i64,
	pub depth: usize,
}

pub struct ProceduralGenerator;

/// First pass at procedural generation will be nothing more than simple depth-maps.
impl ProceduralGenerator {
    pub fn generate_chunk(x: i64, y: u8, w: &mut world::World) {
    	let curr_chunk = chunk::Coords::from(x, y);

    	let depths = ProceduralGenerator::get_surrounding_depths(curr_chunk.chunk, w);
    	
    	let dl = DepthPoint { x: 0, chunk: curr_chunk.chunk, depth: depths.0 };
    	let dr = DepthPoint { 
    		x: world::chunk::WIDTH - 1, chunk: curr_chunk.chunk, depth: depths.1 
    	};

    	// Initialize edges of chunk to surrounding depths before recursing.
    	ProceduralGenerator::set_depth(&dl, w);
    	ProceduralGenerator::set_depth(&dr, w);

    	// Begin recursion.
    	ProceduralGenerator::midpoint_displacement(&dl, &dr, w);
    }

    fn midpoint_displacement(left: &DepthPoint, right: &DepthPoint, w: &mut world::World) {
    	if right.x - left.x <= 1 {
    		return;
    	}

    	let midpoint = DepthPoint { 
    		x: (left.x + right.x) / 2, chunk: left.chunk,
    		depth: ((left.depth + right.depth) / 2 ) + (rand::random::<usize>() % LIMIT)
    	};

    	ProceduralGenerator::set_depth(&midpoint, w);

    	ProceduralGenerator::midpoint_displacement(left, &midpoint, w);
    	ProceduralGenerator::midpoint_displacement(&midpoint, right, w);
    }

    // Assuming (x,y) is the top left corner of a chunk, 
    fn get_surrounding_depths(c: i64, w: &world::World) -> (usize, usize) {
    	(ProceduralGenerator::calculate_depth(world::chunk::WIDTH-1, c-1, w), 
    		ProceduralGenerator::calculate_depth(0, c+1, w))
    }

    fn calculate_depth(x: usize, c: i64, w: &world::World) -> usize {
    	let xy = chunk::Coords::to_xy(c, x, 0);
    	if let Some(chunk) = w.chunk(xy.0, xy.1) {
			for i in 0..world::HEIGHT {
				let xy = chunk::Coords::to_xy(c, x, i);
				if w.block(xy.0, xy.1) == block::Block::Ground {
            		return i;
            	}
        	}
        	return world::HEIGHT;
    	}
		DEFAULT_DEPTH
    }

    fn set_depth(d: &DepthPoint, w: &mut world::World) {
        // Fill upper blocks with ether.
		for i in 0..d.depth {
			let xy = chunk::Coords::to_xy(d.chunk, d.x, i);
    		w.set_block(xy.0, xy.1, block::Block::Ether);
		}
		// Fill lower blocks with ground.
		for i in d.depth..world::HEIGHT {
			let xy = chunk::Coords::to_xy(d.chunk, d.x, i);
    		w.set_block(xy.0, xy.1, block::Block::Ground);
		}
    }

}
