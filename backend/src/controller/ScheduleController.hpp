
#ifndef ScheduleController_hpp
#define ScheduleController_hpp

#include "service/ScheduleService.hpp"
#include "dto/PageDto.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * User REST controller.
 */
class ScheduleController : public oatpp::web::server::api::ApiController {
public:
  ScheduleController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
private:
  ScheduleService m_scheduleService; // Create user service.
public:

  static std::shared_ptr<ScheduleController> createShared(
    OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
  ){
    return std::make_shared<ScheduleController>(objectMapper);
  }

  ENDPOINT_INFO(getSchedule) {
    info->summary = "get all stored schedule";

    info->addResponse<oatpp::Object<SchedulePageDto>>(Status::CODE_200, "application/json");
    info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
  }
  ADD_CORS(getSchedule)
  ENDPOINT("GET", "schedule/", getSchedule)
  {
    return createDtoResponse(Status::CODE_200, m_scheduleService.getAllSchedule());
  }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif /* ScheduleController_hpp */
