<?php

/**
 * @file
 * Implementation of rules api.
 */

/**
 * Implements hook_rules_evaluator_info().
 */
function loop_notification_rules_evaluator_info() {
  return array(
    'loop_notification' => array(
      'class' => 'LoopNotificationEvaluator',
      'type' => array('text'),
      // Make sure that this evaluator runs before RulesTokenEvaluator which
      // actually replaces tokens with "node" and "user" values.
      'weight' => -100,
    ),
  );
}

/**
 * A RulesDataInputEvaluator used by rules.
 *
 * This replacer replaces [loop:variable_name] tokens in rules content with
 * values of defined variables. We cannot use regular tokens (by implementing
 * `hook_tokens`) as we need to run before the rules module replaces tokens.
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
    return preg_replace_callback('/\[loop:(?<key>[^:]+)\]/', function ($matches) {
      $key = $matches['key'];
      return variable_get($key, '');
    }, $text);
  }

}
