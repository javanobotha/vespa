// Copyright 2017 Yahoo Holdings. Licensed under the terms of the Apache 2.0 license. See LICENSE in the project root.

#include "document_db_reference.h"
#include "gid_to_lid_mapper_factory.h"
#include "gid_to_lid_change_registrator.h"
#include <vespa/searchcore/proton/documentmetastore/documentmetastore.h>
#include <vespa/searchlib/attribute/attributeguard.h>
#include <vespa/searchlib/attribute/iattributemanager.h>

namespace proton {

DocumentDBReference::DocumentDBReference(std::shared_ptr<search::IAttributeManager> attrMgr,
                                         std::shared_ptr<DocumentMetaStore> dms,
                                         std::shared_ptr<IGidToLidChangeHandler> gidToLidChangeHandler)
    : _attrMgr(std::move(attrMgr)),
      _dms(std::move(dms)),
      _gidToLidChangeHandler(std::move(gidToLidChangeHandler))
{
}

DocumentDBReference::~DocumentDBReference()
{
}

std::shared_ptr<search::AttributeVector>
DocumentDBReference::getAttribute(vespalib::stringref name)
{
    search::AttributeGuard::UP guard = _attrMgr->getAttribute(name);
    if (guard) {
        return guard->getSP();
    } else {
        return std::shared_ptr<search::AttributeVector>();
    }
}

std::shared_ptr<search::IGidToLidMapperFactory>
DocumentDBReference::getGidToLidMapperFactory()
{
    return std::make_shared<GidToLidMapperFactory>(_dms);
}

std::unique_ptr<GidToLidChangeRegistrator>
DocumentDBReference::makeGidToLidChangeRegistrator(const vespalib::string &docTypeName)
{
    return std::make_unique<GidToLidChangeRegistrator>(_gidToLidChangeHandler, docTypeName);
}

} // namespace proton
