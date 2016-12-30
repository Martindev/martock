//! ProceduralGenerator provides a CL for iteration when new terrain needs to be generated.
//!
//! There can only be one ProceduralGenerator modifying the world.
//!
//! ProceduralGenerator is responsible for generating chunks of blocks as needed.
//!
//! ProceduralGenerator creates blocks in complete vertical slices; we expand horizontally.

use block;
use committer;
use world;

pub struct ProceduralGenerator {

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