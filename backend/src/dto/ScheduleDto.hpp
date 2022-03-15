/**
 * Файл со Объектом "Расписание"
 */
#ifndef ScheduleDto_hpp
#define ScheduleDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Стуктура отображающая объект "Расписание", повторяет поля в БД
 */
class ScheduleDto : public oatpp::DTO {
  
  DTO_INIT(ScheduleDto, DTO)

  DTO_FIELD(Int32, schedule_id);
  DTO_FIELD(String, class_name, "class_name");
  DTO_FIELD(String, subjects, "subjects");
  DTO_FIELD(String, week_day, "week_day");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* ScheduleDto_hpp */
