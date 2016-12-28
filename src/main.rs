mod block;
mod body;
mod commit;
mod committer;
mod tool;
mod world;

struct Sentience<'a> {
    bodies: Vec<&'a body::Body>,
    committers: Vec<&'a committer::Committer>,
}

fn arbite(_: &mut world::World, _: commit::Commit) {}

fn arbiter(w: &mut world::World, cls: &[committer::CL]) {
    for cl in cls {
        for commit in cl.commits() {
            arbite(w, commit);
        }
    }
}

fn reality(_: &world::World, _: &mut [&body::Body]) {}

fn engine(mut w: world::World, mut sentience: Sentience) {
    loop {
        let mut cls = Vec::new();
        for c in sentience.committers.iter() {
            if let Some(cl) = c.cl(&w, &sentience.bodies) {
                cls.push(cl);
            }
        }

        arbiter(&mut w, cls.as_slice());
        reality(&w, sentience.bodies.as_mut_slice());
    }
}

fn main() {
    let w = world::World::new();
    let s = Sentience{
        bodies: Vec::new(),
        committers: Vec::new(),
    };
    engine(w, s);
}
