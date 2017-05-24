__kernel void closest_unit(
  const __global float2 * units,
  const __global int * team_ids,
  __global float3 * closest_enemy_units,
  __global float3 * closest_friendly_units,
  const unsigned int count
) {
  unsigned int gid = get_global_id(0);
  if (gid >= count) {
    return;
  }
  const float3 unit;
  unit.xy = units[gid];
  unit.z = MAXFLOAT;
  const int team_id = team_ids[gid];

  float3 closest_friendly_unit = unit;
  float3 closest_enemy_unit = unit;

  for (unsigned int i = 0; i < count; i++) {
    if (i == gid) {
      continue;
    }
    float3 current_unit;
    current_unit.xy = units[i];
    const float2 diff = current_unit.xy - unit.xy;
    current_unit.z = diff.x * diff.x + diff.y * diff.y;
    const int current_team_id = team_ids[i];
    if (current_team_id == team_id) {
      if (current_unit.z < closest_friendly_unit.z) {
        closest_friendly_unit = current_unit;
      }
    } else if (current_unit.z < closest_enemy_unit.z) {
      closest_enemy_unit = current_unit;
    }
  }

  closest_friendly_units[gid] = closest_friendly_unit;
  closest_enemy_units[gid] = closest_enemy_unit;
}
