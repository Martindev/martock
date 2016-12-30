//! ProceduralGenerator provides a CL for iteration when new terrain needs to be generated.
//!
//! There can only be one ProceduralGenerator modifying the world.
//!
//! ProceduralGenerator is responsible for generating chunks of blocks as needed.
//!
//! ProceduralGenerator creates blocks 

use block;
use committer;
use world;

let chunk_width, world_height = 0;

pub type Chunk = [ [Block; chunk_width]; world_height]

pub struct ProceduralGenerator {
	next_chunk: Chunk

}

impl ProceduralGenerator {
	fn
}

impl committer:Committer for ProceduralGenerator {
	fn cl(&self, w: &world::World) -> Option<Box<CL>> {
		None
	}
}

impl CL for ProceduralGenerator {
	fn next(&mut self) -> Option<Self::Item> {
		None
	}
}