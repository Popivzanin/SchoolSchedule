
#ifndef CRUD_SCHEDULESERVICE_HPP
#define CRUD_SCHEDULESERVICE_HPP

#include "db/UserDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class ScheduleService {
private:
  typedef oatpp::web::protocol::http::Status Status;
private:
  OATPP_COMPONENT(std::shared_ptr<UserDb>, m_database); // Inject database component
public:
  oatpp::Object<PageDto<oatpp::Object<ScheduleDto>>> getAllSchedule();

};

#endif //CRUD_SCHEDULESERVICE_HPP
