<?php

namespace Drupal\views_polygon_search\Plugin\views\filter;

use Drupal\views\Plugin\views\filter\FilterPluginBase;

/**
 * A handler to provide a field that is completely custom by the administrator.
 *
 * @ingroup views_field_handlers
 *
 * @ViewsFilter("polygon_filter")
 */
class PolygonFilter extends FilterPluginBase {
  protected $alwaysMultiple = TRUE;
  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->ensureMyTable();

    $field = $this->realField . '_value';


    $field = "$this->tableAlias.{$field}";

    $query = $this->query;

    $value = is_array($this->value) ? reset($this->value) : $this->value;
    $geom = \geoPHP::load($value, 'wkt');
    if ($geom) {
      /* @var $query \Drupal\views\Plugin\views\query\Sql */
      $query->addWhereExpression($this->options['group'], 'ST_Contains(ST_GeomFromText(:polygon), ST_GeomFromText(' . $field . '))', array(':polygon' => $value));
    }
  }

  /**
   * Provide a simple textfield for equality
   */
  protected function valueForm(&$form, \Drupal\Core\Form\FormState $form_state) {
    $form['value'] = [
      '#type' => 'textarea',
      '#title' => t('WKT'),
      '#default_value' => $this->value,
    ];

  }
}
