//! ProceduralGenerator provides a CL for iteration when new terrain needs to be generated.
//!
//! There can only be one procedural generator modifying the world.
//!
//! The procedural generator is responsible for generating chunks of blocks as needed.
//!
//! The procedural generator creates blocks in complete vertical slices; we expand horizontally.
//!
//! Unlike other actors which implement committer, the procedural generator has mutable access to 
//! world.

use block;
use committer;
use world;

pub struct ProceduralGenerator {

}

impl ProceduralGenerator {
	fn 
}
