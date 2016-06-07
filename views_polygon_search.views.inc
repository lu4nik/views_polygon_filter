<?php

/**
 * @file.
 * Views integration.
 */

/**
 * Implements hook_field_views_data().
 */
/**
 * Implements hook_field_views_data_alter().
 */
function views_polygon_search_field_views_data_alter(array &$data, \Drupal\field\FieldStorageConfigInterface $field_storage) {
if ($field_storage->getType() != 'geofield') {
  return;
}
  // Make sure views.views.inc is loaded.
  module_load_include('inc', 'views', 'views.views');
//  return;

  // Get the default data from the views module.
//  $data = views_field_default_views_data($field_storage);

  // Loop through all of the results and set our overrides.
  foreach ($data as $table_name => $table_data) {
    $args = ['@field_name' => $field_storage->getName()];

    $target_entity_type = \Drupal::entityTypeManager()->getDefinition($field_storage->getTargetEntityTypeId());
    $field_coordinates_table_data = $data[$target_entity_type->getBaseTable() . '__' . $field_storage->getName()][$field_storage->getName()];

    // Add proximity handlers.
    $data[$table_name][$args['@field_name'] . '_polygon_filter'] = [
      'group' => 'Content',
      'title' => t('Polygon (@field_name)', $args),
      'title short' => $field_coordinates_table_data['title short'] . t(":polygon"),
      'help' => $field_coordinates_table_data['help'],
      'filter' => [
        'id' => 'polygon_filter',
        'table' => $table_name,
        'entity_type' => $field_storage->get('entity_type'),
        'field_name' => $args['@field_name'].'_polygon',
        'real field' => $args['@field_name'],
        'label' => t('Polygon filter for !field_name', $args),
        'allow empty' => TRUE,
        'additional fields' => [
          $args['@field_name'].'_geo_type',
          $args['@field_name'].'_lat',
          $args['@field_name'].'_lon',
          $args['@field_name'].'_left',
          $args['@field_name'].'_top',
          $args['@field_name'].'_right',
          $args['@field_name'].'_bottom',
          $args['@field_name'].'_geohash',
        ],
      ],
    ];
  }

  return $data;
}

/**
 * Implements hook_views_data_alter().
 */
function views_polygon_search_views_data_alter(array &$data) {
//  debug($data, 1);
$z = 0;
}
