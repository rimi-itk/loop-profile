<?php

/**
 * @file
 */

/**
 * Implements hook_rules_evaluator_info().
 */
function loop_notification_rules_evaluator_info() {
  return array(
    'loop_notification' => array(
      'class' => 'LoopNotificationEvaluator',
      'type' => array('text'),
      'weight' => -100,
    ),
  );
}

/**
 *
 */
class LoopNotificationEvaluator extends RulesDataInputEvaluator {

  /**
   * {@inheritdoc}
   */
  public function prepare($text, $variables) {
  }

  /**
   * {@inheritdoc}
   */
  public function evaluate($text, $options, RulesState $state) {
    // Replace [loop:variable_name] with value of variable "variable_name".
    return preg_replace_callback('/\[loop:(?:(?<type>[^:]+):)?(?<key>[^:]+)\]/', function ($matches) {
      $type = $matches['type'];
      $key = $matches['key'];
      if (empty($type) || $type === 'var' || $type === 'variable') {
        return variable_get($key, '');
      }

      return $matches[0];
    }, $text);
  }

}
