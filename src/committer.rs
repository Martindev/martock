use body;
use commit;
use world;

pub trait CL {
    fn commits(&self) -> Iterator<Item=commit::Commit>;
}

pub trait Committer {
    fn cl(&world::World, &[&body::Body]) -> Option<Box<CL>>;
}
