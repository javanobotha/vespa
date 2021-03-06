// Copyright 2017 Yahoo Holdings. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#include "documentdb_commit_job.h"
#include "icommitable.h"

namespace proton {

DocumentDBCommitJob::DocumentDBCommitJob(ICommitable & committer, fastos::TimeStamp visibilityDelay) :
    IMaintenanceJob("documentdb_commit", visibilityDelay.sec(), visibilityDelay.sec()),
    _committer(committer)
{
}

bool
DocumentDBCommitJob::run()
{
    _committer.commit();
    return true;
}

} // namespace proton
