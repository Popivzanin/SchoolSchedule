#include "ScheduleService.hpp"

oatpp::Object<PageDto<oatpp::Object<ScheduleDto>>> ScheduleService::getAllSchedule() {

  auto dbResult = m_database->getAllSchedule();
  OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

  auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<ScheduleDto>>>();

  auto rsp = PageDto<oatpp::Object<ScheduleDto>>::createShared();
//  rsp->offset = 1;
//  rsp->limit = 1;
  rsp->count = items->size();
  rsp->items = items;

  return rsp;
}
