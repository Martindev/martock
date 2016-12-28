use commit;

pub trait CL: Iterator<Item=commit::Commit> {}
