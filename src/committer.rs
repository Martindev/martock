use body;
use commit;
use world;

pub trait CL {
    fn commits(&self) -> Iterator<Item=commit::Commit>;
}

pub trait Committer<'a> {
    fn cl(&self, &world::World, &[&body::Body]) -> Option<&'a CL>;
}
